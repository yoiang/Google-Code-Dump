#include "ModelPolygon.h"

ModelPolygon::ModelPolygon() : m_iNumVertices(0), m_pVertices(0), m_ptAverageNormal(0, 0, 0),
								m_uiTextureID(0), m_ptBBNegative(0, 0, 0),
								m_ptBBPositive(0, 0, 0)
{
}

ModelPolygon::ModelPolygon(int iSetNumVertices) : m_pVertices(0), m_ptAverageNormal(0, 0, 0), 
								m_uiTextureID(0), m_ptBBNegative(0, 0, 0),
								m_ptBBPositive(0, 0, 0)
{
	SetNumVertices(iSetNumVertices) ;
}

ModelPolygon::~ModelPolygon()	// model destructor
{
	if (m_pVertices != 0) delete [] m_pVertices ;
}

void ModelPolygon::SetNumVertices(const int &iSetNumVertices)
{
	if (m_pVertices != 0) 
	{
		if (m_iNumVertices < iSetNumVertices)
		{
			delete [] m_pVertices ;
			m_pVertices = new ModelVertex[iSetNumVertices] ;
		}
	} else
	{
		m_pVertices = new ModelVertex[iSetNumVertices] ;
	}
	m_iNumVertices = iSetNumVertices ;
}

void ModelPolygon::GetNumVertices(int &iGetNumVertices) 
{
	iGetNumVertices = m_iNumVertices ;
}

bool ModelPolygon::SetVertex(const int &iVertexIndex, const ModelVertex &SetVertex)
{
	if (iVertexIndex >= m_iNumVertices || iVertexIndex < 0) return false ;

	m_pVertices[iVertexIndex] = SetVertex ;
	return true ;
}

bool ModelPolygon::GetVertex(const int &iVertexIndex, ModelVertex &GetVertex)
{
	if (iVertexIndex >= m_iNumVertices || iVertexIndex < 0) return false ;

	GetVertex = m_pVertices[iVertexIndex] ;
	return true ;
}
	
void ModelPolygon::SetTextureID(const unsigned int &uiSetTextureID)
{
	m_uiTextureID = uiSetTextureID ;
}

void ModelPolygon::GetTextureID(unsigned int &uiGetTextureID)
{
	uiGetTextureID = m_uiTextureID ;
}
	
void ModelPolygon::SetAverageNormal(const Point &ptSetAverageNormal)
{
	m_ptAverageNormal = ptSetAverageNormal ;
}

void ModelPolygon::GetAverageNormal(Point &ptGetAverageNormal)
{
	ptGetAverageNormal = m_ptAverageNormal ;
}

void ModelPolygon::SetBBNegative(const Point &ptSetBBNegative)
{
	m_ptBBNegative = ptSetBBNegative ;
}

void ModelPolygon::GetBBNegative(Point &ptGetBBNegative)
{
	ptGetBBNegative = m_ptBBNegative ;
}

void ModelPolygon::SetBBPositive(const Point &ptSetBBPositive)
{
	m_ptBBPositive = ptSetBBPositive ;
}

void ModelPolygon::GetBBPositive(Point &ptGetBBPositive)
{
	ptGetBBPositive = m_ptBBPositive ;
}
