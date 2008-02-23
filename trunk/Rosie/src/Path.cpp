#include "Path.h"

PathNode::PathNode()
{
	iNumSteps = 0 ;
}

Path::Path()
{
	bConnectEnd = false ;
	bLoop = false ;
}

Path::~Path()
{
	PathList.Clear(true) ;
}

void Path::Add(Point ptSetVertex, int iSetNumSteps)
{
	PathNode *pTemp = new PathNode ;
	pTemp->ptVertex = ptSetVertex ;
	pTemp->iNumSteps = iSetNumSteps ;

	PathList.AddBack(pTemp) ;
}

void Path::Add(PointType dSetX, PointType dSetY, PointType dSetZ, int iSetNumSteps)
{
	PathNode *pTemp = new PathNode ;
	pTemp->ptVertex = Point(dSetX, dSetY, dSetZ) ;
	pTemp->iNumSteps = iSetNumSteps ;

	PathList.AddBack(pTemp) ;
}

Point Path::StartingPoint()
{
	iIterationCount = -1 ;
	pPlace = PathList.pHead ;
	if (pPlace != 0) return pPlace->pValue->ptVertex ;
	return Point(0,0,0) ;
}

Point Path::StepForward()
{
	if (iIterationCount == -1 || iIterationCount >= pPlace->pValue->iNumSteps)
	{
		if (pPlace->pNext == 0)
		{
			if (bLoop)
			{
				if (bConnectEnd) 
				{
					Point ptTemp = PathList.pHead->pValue->ptVertex - pPlace->pValue->ptVertex ;
					pPlace = PathList.pHead ;
					ptIterater = ptTemp / float(pPlace->pValue->iNumSteps) ;
					iIterationCount = 1 ;
					return ptIterater ;
				} else return (StartingPoint() - PathList.pTail->pValue->ptVertex) ;
			} else
			{
				return Point(0, 0, 0) ;
			}
		} else
		{
			Point ptTemp = pPlace->pNext->pValue->ptVertex - pPlace->pValue->ptVertex ;
			pPlace = pPlace->pNext ;
			ptIterater = ptTemp / float(pPlace->pValue->iNumSteps) ;
			iIterationCount = 1 ;
			return ptIterater ;
		}
	} else
	{
		iIterationCount ++ ;
		return ptIterater ;
	}
}
