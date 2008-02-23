#include "Path.h"

PathNode::PathNode() : m_iNumSteps(0)
{
}

Path::Path() : m_bConnectEnd(false)
{
}

Path::~Path()
{
	m_iterPlace = m_lPathList.begin() ;
}

void Path::Add(Point ptSetVertex, int iSetNumSteps)
{
	PathNode *pTemp = new PathNode ;
	pTemp->m_ptVertex = ptSetVertex ;
	pTemp->m_iNumSteps = iSetNumSteps ;

	m_lPathList.push_back(pTemp) ;
}

void Path::Add(PointType dSetX, PointType dSetY, PointType dSetZ, int iSetNumSteps)
{
	PathNode *pTemp = new PathNode ;
	pTemp->m_ptVertex = Point(dSetX, dSetY, dSetZ) ;
	pTemp->m_iNumSteps = iSetNumSteps ;

	m_lPathList.push_back(pTemp) ;
}

Point Path::StartingPoint()
{
	m_iIterationCount = -1 ;
	m_iterPlace = m_lPathList.begin() ;
	if (m_iterPlace != m_lPathList.end()) return (*m_iterPlace)->m_ptVertex ;
	return Point(0,0,0) ;
}

Point Path::StepForward()
{
	/*
	std::list<PathNode*>::iterator iterNext = m_iterPlace ;
	++ iterNext ;
	if (m_iIterationCount == -1 || m_iIterationCount >= (*m_iterPlace)->m_iNumSteps)
	{
		if (iterNext == m_lPathList.end())
		{
			if (m_bConnectEnd) 
			{
				Point ptTemp = (*m_lPathList.begin())->m_ptVertex - (*m_iterPlace)->m_ptVertex ;
				m_iterPlace = m_lPathList.begin() ;
				m_ptIterater = ptTemp / float((*m_iterPlace)->m_iNumSteps) ;
				m_iIterationCount = 1 ;
				return m_ptIterater ;
			} else return (StartingPoint() - (*m_iterPlace)->m_ptVertex) ;
		} else
		{
			Point ptTemp = pPlace->pNext->pValue->ptVertex - pPlace->pValue->ptVertex ;
			pPlace = pPlace->pNext ;
			ptIterater = ptTemp / float(pPlace->pValue->iNumSteps) ;
			iIterationCount = 1 ;
			return ptIterater ;
		}
	} else*/
	{
		m_iIterationCount ++ ;
		return m_ptIterater ;
	}
}
