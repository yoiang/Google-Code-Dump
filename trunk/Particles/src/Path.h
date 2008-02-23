#ifndef __PATH_H__
#define __PATH_H__

#include <list>
#include "Point.h"

class PathNode 
{
public:
	Point m_ptVertex ;
	int m_iNumSteps ;
	PathNode() ;
} ;

class Path
{
public:
	std::list<PathNode*> m_lPathList ;
	std::list<PathNode*>::iterator m_iterPlace ;

	int m_iIterationCount ;
	Point m_ptIterater ;
	bool m_bConnectEnd ;

	Path() ;
	~Path() ;

	void Add(Point ptSetVertex, int iSetNumSteps) ;
	void Add(PointType dSetX, PointType dSetY, PointType dSetZ, int iSetNumSteps) ;
	Point StartingPoint() ;
	Point StepForward() ;
} ;

#endif